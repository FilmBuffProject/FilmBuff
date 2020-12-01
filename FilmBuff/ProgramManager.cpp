#include "ProgramManager.h"
#include <fstream>

void ProgramManager::initialize()
{
	fstream fileStream(moviesPath);
	string entry;

	while(getline(fileStream, entry))
	{
		/*file format: IMDb movie ID, title, year, genre, description, score
		fields that include a comma will have quotes surrounding them (e.g. a movie with 3 genres 
		will have "genre1, genre2, genre3" rather just genre1 with no quotes around it. The only column guaranteed
		to not have quotes is IMDb movie ID.
		*/


	}
}