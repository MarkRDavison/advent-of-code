namespace mark.davison.advent.of.code.TwentyTwentyFour;

[Day(Year = 2024, Day = 1, Name = "Historian Hysteria")]
public sealed class Day01 : DaySolverBase
{
    public override async Task<(string Part1, string Part2)> Solve(IList<string> input)
    {
        Console.WriteLine("Day01 solver");
        await Task.CompletedTask;

        var items = input.Select(_ => _.Split(" ", StringSplitOptions.RemoveEmptyEntries | StringSplitOptions.TrimEntries)).ToList();

        var list1 = new List<int>();
        var list2 = new List<int>();

        var list2Occurences = new Dictionary<int, int>();

        foreach (var item in items)
        {
            if (item.Length != 2)
            {
                throw new InvalidDataException("Input data was not in expected format");
            }

            list1.Add(int.Parse(item[0]));
            var item2 = int.Parse(item[1]);
            list2.Add(item2);
            if (!list2Occurences.ContainsKey(item2))
            {
                list2Occurences.Add(item2, 1);
            }
            else
            {

                list2Occurences[item2]++;
            }
        }

        var sortedList1 = list1.OrderBy(x => x).ToList();
        var sortedList2 = list2.OrderBy(x => x).ToList();

        var part1 = 0;
        var part2 = 0;

        foreach (var (l1, l2) in sortedList1.Zip(sortedList2))
        {
            part1 += Math.Max(l1, l2) - Math.Min(l1, l2);

            if (list2Occurences.TryGetValue(l1, out int value))
            {
                part2 += l1 * value;
            }
        }

        return (part1.ToString(), part2.ToString());
    }
}
