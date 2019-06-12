#pragma once

#include "nn.h"
#include "ncm.h"
#include "ContentMetaKey.h"
#include "IContentMetaDatabase.h"

namespace nn::ncm
{
	class ContentMetaDatabase : public IContentMetaDatabase
	{
	public:
		ContentMetaDatabase();
		ContentMetaDatabase(ContentMetaDatabase&& db);
		ContentMetaDatabase(nn::sf::SharedPointer<IContentMetaDatabase> db);

		Result Set(const ContentMetaKey& contentMetaKey, const void* buffer, const u64 size);
		Result Get(u64* size, void* buffer, const u64 maxSize, const ContentMetaKey& contentMetaKey);
		Result Remove(const ContentMetaKey& contentMetaKey);
		Result GetContentIdByType(ContentId* contentId, const ContentMetaKey& contentMetaKey, const ContentType& contentType);
		Result ListContentInfo(s32* size, ContentInfo* contentInfo, const s32 maxSize, const ContentMetaKey& contentMetaKey, s32 index);
		Result GetLatest(ContentMetaKey* contentMetaKey, const u64 applicationId);
		Result Has(bool* result, const ContentMetaKey& contentMetaKey);
		Result HasAll(bool* result, const ContentMetaKey*, const s32 size);
		Result GetSize(u64* size, const ContentMetaKey& contentMetaKey);
		Result GetRequiredSystemVersion(u32* version, const ContentMetaKey& contentMetaKey);
		Result GetPatchId(PatchId* patchId, const ContentMetaKey& contentMetaKey);
		Result DisableForcibly();
		Result LookupOrphanContent(bool* result, const ContentId*, s32 size);
		Result Commit();
		Result HasContent(bool* result, const ContentMetaKey& contentMetaKey, const ContentId& contentId);
		Result ListContentMetaInfo(s32* size, ContentMetaInfo* contentMetaInfos, const s32 maxSize, const ContentMetaKey& contentMetaKey, const s32 offset);
		Result GetAttributes(u8* attributes, const ContentMetaKey& contentMetaKey);
		Result GetRequiredApplicationVersion(u32* version, const ContentMetaKey& contentMetaKey);
		Result GetContentIdByTypeAndIdOffset(ContentId* contentId, const ContentMetaKey& contentMetaKey, const ContentType contentType, const u8 offset);


		Result GetControl(ContentId*, ApplicationId, u32);
		Result GetHtmlDocument(ContentId*, ApplicationId, u32);
		Result GetLatestControl(ContentId*, ApplicationId);
		Result GetLatestData(ContentId*, DataId);
		Result GetLatestHtmlDocument(ContentId*, ApplicationId);
		Result GetLatestLegalInformation(ContentId*, ApplicationId);
		Result GetLatestProgram(ContentId*, ProgramId);
		Result GetLegalInformation(ContentId*, ApplicationId, u32);
		
		Result GetProgram(ContentId*, ProgramId, u32);
		
		
		Result Remove(ApplicationId, u32);
		Result Remove(SystemDataId, u32);
		Result Remove(SystemProgramId, u32);
		Result operator=(ContentMetaDatabase&&);
		Result swap(ContentMetaDatabase&);
	};
}