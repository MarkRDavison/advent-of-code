namespace mark.davison.advent.of.code.TwentyTwentyFour;

[Day(Year = 2024, Day = 4, Name = "Ceres Search")]
public sealed class Day04 : DaySolverBase
{
    private static char? GetCharacterAt(int x, int y, IList<string> input)
    {
        if (x < 0 || y < 0 || y >= input.Count || x >= input[y].Length)
        {
            return null;
        }

        return input[y][x];
    }

    private static bool IsXMASPresent(int xStart, int yStart, int xOff, int yOff, IList<string> input)
    {
        return
            GetCharacterAt(xStart, yStart, input) is { } c && c == 'X' &&
            GetCharacterAt(xStart + xOff * 1, yStart + yOff * 1, input) is { } c1 && c1 == 'M' &&
            GetCharacterAt(xStart + xOff * 2, yStart + yOff * 2, input) is { } c2 && c2 == 'A' &&
            GetCharacterAt(xStart + xOff * 3, yStart + yOff * 3, input) is { } c3 && c3 == 'S';
    }
    private static bool IsX_MASPresent(int xStart, int yStart, IList<string> input)
    {
        var nw = GetCharacterAt(xStart - 1, yStart - 1, input);
        var ne = GetCharacterAt(xStart + 1, yStart - 1, input);
        var sw = GetCharacterAt(xStart - 1, yStart + 1, input);
        var se = GetCharacterAt(xStart + 1, yStart + 1, input);

        return
            GetCharacterAt(xStart, yStart, input) is { } c && c == 'A' &&
            ((nw == 'M' && se == 'S') || (nw == 'S' && se == 'M')) &&
            ((ne == 'M' && sw == 'S') || (ne == 'S' && sw == 'M'));
    }

    public override Task<(string Part1, string Part2)> Solve(IList<string> input)
    {
        var part1 = 0;
        var part2 = 0;

        for (int y = 0; y < input.Count; ++y)
        {
            for (int x = 0; x < input[y].Length; ++x)
            {
                if (GetCharacterAt(x, y, input) is { } c && c == 'X')
                {
                    // N
                    if (IsXMASPresent(x, y, 0, -1, input))
                    {
                        part1++;
                    }

                    // E
                    if (IsXMASPresent(x, y, +1, 0, input))
                    {
                        part1++;
                    }

                    // S
                    if (IsXMASPresent(x, y, 0, +1, input))
                    {
                        part1++;
                    }
                    // W
                    if (IsXMASPresent(x, y, -1, 0, input))
                    {
                        part1++;
                    }

                    // NE
                    if (IsXMASPresent(x, y, +1, -1, input))
                    {
                        part1++;
                    }
                    // SE
                    if (IsXMASPresent(x, y, +1, +1, input))
                    {
                        part1++;
                    }
                    // SW
                    if (IsXMASPresent(x, y, -1, +1, input))
                    {
                        part1++;
                    }
                    // NW
                    if (IsXMASPresent(x, y, -1, -1, input))
                    {
                        part1++;
                    }
                }
                else
                {
                    if (IsX_MASPresent(x, y, input))
                    {
                        part2++;
                    }
                }
            }
        }

        return Task.FromResult((part1.ToString(), part2.ToString()));
    }
}
