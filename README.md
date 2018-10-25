Implementation of an ECS in Regular ol' C

Current implementation supports required grouping with an O(n) retrieval and placing of components (could be improved to O(1))

System is currently setup as such:

Manager has control of a map of groups which have a linked list of potential entities.

Each entity possess a set maximum of components (32 in this case). These components hold the actual data as the entities are just empty containers.

Main functionality is adding and getting components as well as adding entities to the manager.

TODO: adding an assetmanager to create a factory design pattern.