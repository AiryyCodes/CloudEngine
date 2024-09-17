#include "CloudEngine/entry.h"
#include <cstdio>
#include <cstdlib>

int main()
{
	printf("Starting engine...\n");

	printf("Initializing game...\n");	
	CEEntry* entry = CEInit();
	
	entry->Init();
	printf("Game initialized!\n");

	entry->Start();
	entry->Update();
	entry->Exit();

	return EXIT_SUCCESS;
}
