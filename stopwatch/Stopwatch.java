package lynx.util;

import java.util.concurrent.TimeUnit;

/**
 * A class for accurately measuring execution time of arbitrary code.
 * <p>
 * This class provides a convenient abstraction for timings and should be
 * preferred over direct calls to {@link System#nanoTime}. Note that using
 * {@link System#currentTimeMillis} for measuring elapsed time is incorrect
 * because it measures wall-clock time (in addition to having low resolution
 * - on the order of 10ms on most systems - which is quite poor for timings).
 * <p>
 * <p>
 * Basic usage:
 * <pre>
 *     Stopwatch stopwatch = new Stopwatch();
 *     stopwatch.start();
 *     doSomething();
 *     stopwatch.stop();	// The call to stop() is optional.
 *
 *     System.out.println("Elapsed time: " + stopwatch.getTime());
 * </pre>
 * <p>
 * <p>
 * Even though calling stop(), split() or suspend() (to make the intent explicit
 * and obtain accurate results) before measuring is the recommended approach,
 * getting a measurement at any point in time will return an appropriate result.
 * </p>
 * <p>
 * The class protects against any inappropriate calls of its methods.
 * </p>
 * <p>
 * <strong>Note: This class is not thread-safe.</strong>
 * </p>
 *
 * @author Vasilis Poulimenos
 */
public final class Stopwatch {

	/**
	 * Use System.nanoTime (measures elapsed time) instead of
	 * System.currentTimeMillis (measures wall-clock time).
	 *
	 * http://stackoverflow.com/q/351565/1751037
	 * http://stackoverflow.com/q/1770010/1751037
	 * http://www.javapractices.com/topic/TopicAction.do?Id=85
	 *
	 * @return the value returned by System.nanoTime
	 */
	private static final long getSystemTime() {
		return System.nanoTime();
	}

	/**
	 * Enum type indicating the state of the stopwatch.
	 */
	private enum State {
		READY,
		RUNNING,
		STOPPED,
		SUSPENDED
	}

	/**
	 * The current state of the stopwatch.
	 */
	private State state;
	private boolean issplit;

	private long startTime;
	private long stopTime;

	/**
	 * Utility method that performs the (re)initialization of the stopwatch.
	 */
	private final void init() {
		startTime = 0;
		stopTime = 0;
		issplit = false;
		state = State.READY;
	}

	/**
	 * Constructs a new Stopwatch.
	 */
	public Stopwatch() {
		init();
	}

	/**
	 * Returns a string representation of the current elapsed time.
	 * The following format is used: hours:minutes:seconds.milliseconds.
	 *
	 * @return the elapsed time as a string
	 */
	@Override
	public String toString() {
		// http://stackoverflow.com/a/625624/1751037
		final long millis = getTime(),
			seconds = TimeUnit.MILLISECONDS.toSeconds(millis) % 60,
			minutes = TimeUnit.MILLISECONDS.toMinutes(millis) % 60,
			hours = TimeUnit.MILLISECONDS.toHours(millis);
		return String.format("%d:%d:%d.%d", hours, minutes, seconds, millis);
	}

	/**
	 * Starts the stopwatch.
	 *
	 * @return this
	 * @throws IllegalStateException if the stopwatch is already started.
	 */
	public Stopwatch start() {
		if (state != State.READY) {
			throw new IllegalStateException("The stopwatch is already started");
		}
		startTime = getSystemTime();
		state = State.RUNNING;
		return this;
	}

	/**
	 * Stops the stopwatch.
	 *
	 * @return this
	 * @throws IllegalStateException if the stopwatch is not already started.
	 */
	public Stopwatch stop() {
		if (state != State.RUNNING && state != State.SUSPENDED) {
			throw new IllegalStateException("The stopwatch is not started");
		}
		if (state == State.RUNNING) {
			stopTime = getSystemTime();
		}
		state = State.STOPPED;
		return this;
	}

	/**
	 * Suspends the stopwatch.
	 * The stopwatch can be resumed later on with a call to the resume method.
	 * While suspended, the stopwatch will not keep track of the elapsed time.
	 *
	 * @return this
	 * @throws IllegalStateException if the stopwatch is not running.
	 */
	public Stopwatch suspend() {
		if (state != State.RUNNING) {
			throw new IllegalStateException("The stopwatch is not running");
		}
		stopTime = getSystemTime();
		state = State.SUSPENDED;
		return this;
	}

	/**
	 * Resumes the stopwatch.
	 * The stopwatch will start measuring the elapsed time again.
	 * The time while suspended is not included in the total time.
	 *
	 * @return this
	 * @throws IllegalStateException if the stopwatch is not suspended.
	 */
	public Stopwatch resume() {
		if (state != State.SUSPENDED) {
			throw new IllegalStateException("The stopwatch is not suspended");
		}
		// Advance start time by the time suspended.
		startTime += getSystemTime() - stopTime;
		state = State.RUNNING;
		return this;
	}

	/**
	 * Resets the stopwatch.
	 * This method brings the stopwatch to its initial state, allowing it to be
	 * reused for new timings. In contrast to other methods, it can be called at
	 * any point in time.
	 *
	 * @return this
	 */
	public Stopwatch reset() {
		init();
		return this;
	}

	/**
	 * Restarts the stopwatch.
	 * Equivalent to: stopwatch.reset().start()
	 *
	 * @return this
	 */
	public Stopwatch restart() {
		return reset().start();
	}

	/**
	 * Splits the time.
	 * This method sets the stop time of the stopwatch,
	 * allowing the recorded split time to be read.
	 *
	 * @return this
	 * @throws IllegalStateException if the stopwatch is not running.
	 */
	public Stopwatch split() {
		if (state != State.RUNNING) {
			throw new IllegalStateException("The stopwatch is not running");
		}
		stopTime = getSystemTime();
		issplit = true;
		return this;
	}

	/**
	 * Erases the last recorded split time.
	 * This method clears the stop time of the stopwatch.
	 *
	 * @return this
	 */
	public Stopwatch unsplit() {
		if (!issplit) {
			throw new IllegalStateException("No split time recorded.");
		}
		stopTime = 0;
		issplit = false;
		return this;
	}

	/**
	 * Returns the time on the stopwatch.
	 * The reported elapsed time can be one of the following:
	 * 		1. The interval between the start time and the stop time.
	 * 		2. The interval between the start time and the time this method is
	 * 			called.
	 * 		3. The interval between the start time and the time the stopwatch
	 * 			was suspended.
	 * 		4. The last recorded split time.
	 * Note that due to the overhead incurred by the measurements of the
	 * stopwatch in addition to possible system inaccuracies, specifying
	 * TimeUnit.NANOSECONDS precision may yield meaningless results.
	 *
	 * @param desiredUnit the desired time unit
	 * @return the elapsed time in the desired time unit
	 */
	public long getTime(TimeUnit desiredUnit) {
		if (state == State.RUNNING && !issplit) {
			return desiredUnit.convert(
				getSystemTime() - startTime, TimeUnit.NANOSECONDS);
		}
		return desiredUnit.convert(stopTime - startTime, TimeUnit.NANOSECONDS);
	}

	/**
	 * Returns the time on the stopwatch.
	 * @return the elapsed time in milliseconds
	 * @see #getTime(TimeUnit)
	 */
	public long getTime() {
		return getTime(TimeUnit.MILLISECONDS);
	}

}
