namespace mark.davison.advent.of.code.TwentyTwentyFour;

[Day(Year = 2024, Day = 2, Name = "Red-Nosed Reports")]
public sealed class Day02 : DaySolverBase
{
    public override Task<(string Part1, string Part2)> Solve(IList<string> input)
    {
        var reports = new List<List<int>>();

        foreach (var line in input)
        {
            var parts = line.Split(' ');

            reports.Add([.. parts.Select(int.Parse)]);
        }

        var part1 = 0;
        var part2 = 0;

        foreach (var report in reports)
        {
            if (IsReportSafe(report))
            {
                part1++;
                part2++;
            }
            else
            {
                for (int i = 0; i < report.Count; ++i)
                {
                    var smallerReport = report.ToList();
                    smallerReport.RemoveAt(i);

                    if (IsReportSafe(smallerReport))
                    {
                        part2++;
                        break;
                    }
                }
            }
        }

        return Task.FromResult((part1.ToString(), part2.ToString()));
    }

    public static bool IsReportSafe(List<int> report)
    {
        bool? increasing = null;
        for (int i = 1; i < report.Count; ++i)
        {
            var lhs = report[i - 1];
            var rhs = report[i];


            if (Math.Abs(lhs - rhs) < 1 ||
                Math.Abs(lhs - rhs) > 3)
            {
                return false;
            }

            if (increasing is null)
            {
                increasing = lhs < rhs;
            }
            else
            {
                var thisIncreasing = lhs < rhs;

                if (thisIncreasing != increasing)
                {
                    return false;
                }

            }
        }

        return true;
    }
}
