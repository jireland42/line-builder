#include <array>
#include <iostream>
#include <limits>
#include <vector>

enum class Iron
{
	Cross,
	Tee,
	Valve,
	Pipe
};

constexpr size_t max_stream_size{std::numeric_limits<std::streamsize>::max()};

auto get_num_wells() -> size_t
{
	constexpr size_t min_wells{2};
	constexpr size_t max_wells{5};

	std::cout << "Enter the number of wells to tie in [supports from ";
   	std::cout << min_wells << " to " << max_wells << " wells] (ctrl-c to quit): ";

	size_t num_wells;
	while(!(std::cin >> num_wells) || num_wells > max_wells || num_wells < 2)
	{
		std::cout << "You must enter a number from " << min_wells << " to " << max_wells;
		std::cout << " continue (ctrl-c to quit): ";
		std::cin.clear();
		std::cin.ignore(max_stream_size, '\n');
	}
	std::cout << '\n';

	return num_wells;
}

auto get_well_spacings(size_t num_wells) -> std::vector<size_t>
{
	constexpr size_t min_well_spacing{314}; // 78.5"/2m chosen arbitrarily
	constexpr size_t max_well_spacing{2362}; // 590.5"/15m chosen arbitrarily

	std::vector<size_t> well_spacings(num_wells - 1);

	for (size_t i{1}; i < num_wells; i += 1)
	{
		size_t well_spacing;
		std::cout << "Enter the well spacing between wells " << i << " and " << i + 1 << " in 0.25\" increments: ";
		while (
			!(std::cin >> well_spacing)
			|| well_spacing > max_well_spacing
			|| well_spacing < min_well_spacing)
		{
			std::cout <<
				"You must enter a number between " << min_well_spacing << " "
				"and " << max_well_spacing << " to select an option. Please try again (ctrl-c to quit): ";
			std::cin.clear();
			std::cin.ignore(max_stream_size, '\n');
		}
		std::cout << '\n';

		well_spacings[i - 1] = well_spacing;
	}

	return well_spacings;
}

auto get_tie_in_position(size_t num_wells) -> size_t
{
	std::cout <<
		"Standing on the side of the well bank with the manifold and counting the wells from "
		"left to right as 1, 2, etc., where does frac tie in?\n";
	std::cout << "\t1) To the left of well 1.\n";
	for (size_t i{1}; i < num_wells; i += 1)
	{
		std::cout << "\t" << i + 1 << ") Between wells " << i << " and " << i + 1 << ".\n";
	}
	std::cout << "\t" << num_wells + 1 << ") To the right of well " << num_wells << ".\n\n";
	std::cout << "Press the key of the corresponding option (ctrl-c to quit).\n";

	size_t tie_in_position;
	while (!(std::cin >> tie_in_position) || tie_in_position > num_wells + 1 || tie_in_position == 0)
	{
		std::cout <<
			"You must enter a number between 1 and " << num_wells + 1 << " to select an "
			"option. Please try again (ctrl-c to quit): ";
		std::cin.clear();
		std::cin.ignore(max_stream_size, '\n');
	}
	std::cout << '\n' << '\n';

	return tie_in_position;
}

int main()
{
	// 16.75" ~ 67*0.25"
	// 3' ~ 144*0.25"
	// 4' ~ 192*0.25"
	// 5' ~ 240*0.25"
	// 8' ~ 384*0.25"
	// 10' ~ 480*0.25"
	constexpr std::array<size_t,6> pipe_lengths{67, 144, 192, 240, 384, 480};

	size_t const num_wells{get_num_wells()};
	std::vector<size_t> const well_spacings{get_well_spacings(num_wells)};
	size_t tie_in_position{get_tie_in_position(num_wells)};

	std::cout << "Wells: " << num_wells << "\n\n";
	std::cout << "Well Spacings: " << '\n';
	for (size_t i{1}; i < num_wells; i += 1)
	{
		std::cout << "\tWell " << i << " to " << i + 1 << ": " << well_spacings[i - 1] << '\n';
	}
	std::cout << '\n';
	std::cout << "Tie-In Position: " << tie_in_position << '\n';

	return 0;
}

