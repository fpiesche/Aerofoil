#include "PLResources.h"

#include "HostFileSystem.h"
#include "MemoryManager.h"
#include "MMHandleBlock.h"
#include "PLPasStr.h"
#include "ResourceManager.h"
#include "ResourceCompiledRef.h"

#include <assert.h>

struct PLOpenedResFile
{
	bool m_isOpen;
};

static const unsigned int kPLMaxOpenedResFiles = 64;
static PLOpenedResFile gs_resFiles[kPLMaxOpenedResFiles];

void DetachResource(Handle hdl)
{
	if (!hdl)
		return;

	PortabilityLayer::MMHandleBlock *block = reinterpret_cast<PortabilityLayer::MMHandleBlock*>(hdl);
	assert(block->m_rmSelfRef);
	assert(block->m_rmSelfRef->m_handle == block);
	block->m_rmSelfRef->m_handle = nullptr;
	block->m_rmSelfRef = nullptr;
}

void ReleaseResource(Handle hdl)
{
	DetachResource(hdl);
	DisposeHandle(hdl);
}

short CurResFile()
{
	return PortabilityLayer::ResourceManager::GetInstance()->GetCurrentResFile();
}

void UseResFile(short fid)
{
	PortabilityLayer::ResourceManager::GetInstance()->SetCurrentResFile(fid);
}

Handle Get1Resource(UInt32 resID, int index)
{
	PL_NotYetImplemented();
	return nullptr;
}

Handle Get1IndResource(UInt32 resID, int index)
{
	PL_NotYetImplemented();
	return nullptr;
}

int Count1Resources(UInt32 resType)
{
	PL_NotYetImplemented();
	return 0;
}

void HCreateResFile(int refNum, long dirID, const PLPasStr &name)
{
	PL_NotYetImplemented();
}

OSErr ResError()
{
	PL_NotYetImplemented();
	return noErr;
}

short FSpOpenResFile(const FSSpec *spec, int permission)
{
	PortabilityLayer::ResourceManager *rm = PortabilityLayer::ResourceManager::GetInstance();

	return rm->OpenResFork(static_cast<PortabilityLayer::EVirtualDirectory>(spec->parID), PLPasStr(spec->name));
}

void CloseResFile(short refNum)
{
	PL_NotYetImplemented();
}

void SetResLoad(Boolean load)
{
	PortabilityLayer::ResourceManager::GetInstance()->SetResLoad(load != 0);
}

long GetMaxResourceSize(Handle res)
{
	const PortabilityLayer::MMHandleBlock *hBlock = reinterpret_cast<PortabilityLayer::MMHandleBlock*>(res);
	const PortabilityLayer::ResourceCompiledRef *resRef = hBlock->m_rmSelfRef;
	return resRef->GetSize();
}

void GetResInfo(Handle res, short *resID, ResType *resType, Str255 resName)
{
	PL_NotYetImplemented();
}

short HOpenResFile(short refNum, long parID, const PLPasStr &name, int permissions)
{
	PL_NotYetImplemented();
	return 0;
}