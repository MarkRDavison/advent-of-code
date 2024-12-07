namespace mark.davison.advent.of.code.framework;

public interface IDaySolver
{
    void Init(string name);

    string Name { get; }

    Task<(string Part1, string Part2)> Solve(IList<string> input);
}
