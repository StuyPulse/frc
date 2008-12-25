/*----------------------------------------------------------------------------*/
/* Copyright (c) FIRST 2008. All Rights Reserved.							  */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in $(WIND_BASE)/WPILib.  */
/*----------------------------------------------------------------------------*/

#ifndef RESOURCE_H_
#define RESOURCE_H_


/**
 * Track resources in the program.
 * The Resource class is a convienent way of keeping track of allocated arbitrary resources
 * in the program. Resources are just indicies that have an lower and upper bound that are
 * tracked by this class. In the library they are used for tracking allocation of hardware channels
 * but this is purely arbitrary. The resource class does not do any actual allocation, but
 * simply tracks if a given index is currently in use.
 * 
 * WARNING: this should only be statically allocated. When the program loads into memory all the
 * static constructors are called. At that time a linked list of all the "Resources" is created.
 * Then when the program actually starts - in the Robot constructor, all resources are initialized.
 * This ensures that the program is restartable in memory without having to unload/reload.
 */
class Resource
{
public:
	virtual ~Resource(void);
	static void CreateResourceObject(Resource **r, UINT32 elements);
	UINT32 Allocate(void);
	UINT32 Allocate(UINT32 index);
	void Free(UINT32 index);

protected:
	Resource(UINT32 size);

private:
	bool *m_isAllocated;
	UINT32 m_size;
	Resource *m_nextResource;

	static Resource *m_resourceList;
};

#endif
