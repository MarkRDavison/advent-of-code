namespace mark.davison.advent.of.code.console;

public class Options
{
    [Option('y', "year", Required = true, HelpText = "The year for the problem.")]
    public int Year { get; set; }

    [Option('d', "day", Required = true, HelpText = "The day for the problem.")]
    public int Day { get; set; }

    [Option('i', "input", Required = false, HelpText = "The input for the problem.")]
    public string? Input { get; set; }

    public string Validate()
    {
        if (Day < 1 || Day > 25)
        {
            return $"The provided day {Day} is invalid, must be between 1 and 25";
        }

        if (!string.IsNullOrEmpty(Input) && !File.Exists(Input))
        {
            return $"The provided input '{Input}' is invalid, must point to a file";
        }

        return string.Empty;
    }
}

internal class Program
{
    static string ToElapsed(TimeSpan ts)
    {
        return ts.Days != 0 ? $"{ts.Days} days"
             : ts.Hours != 0 ? $"{ts.Hours} hours"
             : ts.Minutes != 0 ? $"{ts.Minutes} minutes"
             : ts.Seconds != 0 ? $"{ts.Seconds} seconds"
             : ts.Milliseconds != 0 ? $"{ts.Milliseconds} milliseconds"
             : ts.Microseconds != 0 ? $"{ts.Microseconds} microseconds"
             : $"{ts.Nanoseconds} nanoseconds";
    }

    static void Main(string[] args)
    {
        Parser.Default.ParseArguments<Options>(args)
            .WithParsedAsync<Options>(async options =>
            {
                if (options.Validate() is { } error && !string.IsNullOrEmpty(error))
                {
                    Console.Error.WriteLine(error);
                    return;
                }

                var registration = new PuzzleRegistration();

                registration.RegisterPuzzles();

                var solver = registration.GetSolver(options.Year, options.Day);

                if (solver is null)
                {
                    Console.Error.WriteLine("There is no solver for {0} Day {1}", options.Year, options.Day);

                    return;
                }

                Console.WriteLine("{0} Day {1} - {2}", options.Year, options.Day, solver.Name);

                var sw = Stopwatch.StartNew();

                var (part1, part2) = await solver.Solve([]);

                Console.WriteLine("Part 1: {0}", part1);
                Console.WriteLine("Part 2: {0}", part2);
                Console.WriteLine("Took: {0}", ToElapsed(sw.Elapsed));
                Console.WriteLine();
                Console.WriteLine("Press any key to exit...");
                Console.ReadKey();
            });
    }
}
