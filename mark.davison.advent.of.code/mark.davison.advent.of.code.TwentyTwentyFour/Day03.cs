namespace mark.davison.advent.of.code.TwentyTwentyFour;

[Day(Year = 2024, Day = 3, Name = "Mull It Over")]
public sealed class Day03 : DaySolverBase
{
    public override Task<(string Part1, string Part2)> Solve(IList<string> input)
    {
        var part1 = 0;
        var part2 = 0;

        var enabled = true;

        foreach (var line in input)
        {
            for (int i = 0; i < line.Length; ++i)
            {
                var start = line.AsSpan(i);

                if (start.StartsWith("do()"))
                {
                    enabled = true;
                }
                else if (start.StartsWith("don't()"))
                {
                    enabled = false;
                }
                else if (start.StartsWith("mul("))
                {
                    var nextComma = line.IndexOf(',', i + 1);
                    if (nextComma == -1)
                    {
                        continue;
                    }
                    var xStr = line.AsSpan(i + 4, nextComma - i - 4);

                    if (!int.TryParse(xStr, out var x))
                    {
                        continue;
                    }

                    var nextCloseBracket = line.IndexOf(')', i + 4);

                    var yStr = line.AsSpan(nextComma + 1, nextCloseBracket - nextComma - 1);

                    if (!int.TryParse(yStr, out var y))
                    {
                        continue;
                    }

                    part1 += x * y;

                    if (enabled)
                    {
                        part2 += x * y;
                    }
                }
            }
        }

        return Task.FromResult((part1.ToString(), part2.ToString()));
    }
}