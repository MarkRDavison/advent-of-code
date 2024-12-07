namespace mark.davison.advent.of.code.framework;

public class PuzzleRegistration
{
    private readonly Dictionary<int, Dictionary<int, Func<IDaySolver>>> _puzzleCreators = [];

    public void RegisterPuzzles()
    {
        var assemblies = new List<Assembly>();

        var files = Directory.EnumerateFiles(Environment.CurrentDirectory, "mark.davison.advent.of.code*.dll");

        foreach (var file in files)
        {
            assemblies.Add(Assembly.LoadFrom(file));
        }

        var types = assemblies
            .SelectMany(_ => _.GetExportedTypes())
            .Where(_ => _.CustomAttributes.Any(at => at.AttributeType == typeof(DayAttribute)))
            .ToList();

        foreach (var type in types)
        {
            var attribute = type.GetCustomAttribute<DayAttribute>();
            if (attribute is null) { continue; }

            if (!_puzzleCreators.ContainsKey(attribute.Year))
            {
                _puzzleCreators.Add(attribute.Year, []);
            }

            var year = _puzzleCreators[attribute.Year];
            if (year.ContainsKey(attribute.Day))
            {
                Console.Error.WriteLine("Duplicate solver for {0} Day {1}", attribute.Year, attribute.Day);
                continue;
            }

            year.Add(attribute.Day, () =>
            {
                if (Activator.CreateInstance(type) is not IDaySolver solver)
                {
                    throw new InvalidDataException($"Type '{type.Name}' does not implement IDaySolver");
                }

                solver.Init(attribute.Name);

                return solver;
            });
        }
    }

    public IDaySolver? GetSolver(int year, int day)
    {
        if (_puzzleCreators.TryGetValue(year, out var yearSolvers) &&
            yearSolvers.TryGetValue(day, out var creator))
        {
            return creator();
        }

        return null;
    }
}
