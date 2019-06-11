#pragma once

#include "nn.h"
#include "ncm.h"
#include "ContentMetaKey.h"

namespace nn::ncm
{
	class ContentMetaDatabase
	{
	public:
		ContentMetaDatabase();
		ContentMetaDatabase(nn::ncm::ContentMetaDatabase&& db);
		ContentMetaDatabase(nn::sf::SharedPointer<nn::ncm::IContentMetaDatabase> db);
		Result Commit();
		Result DisableForcibly();
		Result Get(u64*, void*, u64, nn::ncm::ContentMetaKey const&);
		Result GetAttributes(u8*, nn::ncm::ContentMetaKey const&);
		Result GetContentIdByType(nn::ncm::ContentId*, nn::ncm::ContentMetaKey const&, nn::ncm::ContentType);
		Result GetContentIdByTypeAndIdOffset(nn::ncm::ContentId*, nn::ncm::ContentMetaKey const&, nn::ncm::ContentType, u8);
		Result GetControl(nn::ncm::ContentId*, nn::ncm::ApplicationId, u32);
		Result GetHtmlDocument(nn::ncm::ContentId*, nn::ncm::ApplicationId, u32);
		Result GetLatest(nn::ncm::ContentMetaKey*, u64);
		Result GetLatestControl(nn::ncm::ContentId*, nn::ncm::ApplicationId);
		Result GetLatestData(nn::ncm::ContentId*, nn::ncm::DataId);
		Result GetLatestHtmlDocument(nn::ncm::ContentId*, nn::ncm::ApplicationId);
		Result GetLatestLegalInformation(nn::ncm::ContentId*, nn::ncm::ApplicationId);
		Result GetLatestProgram(nn::ncm::ContentId*, nn::ncm::ProgramId);
		Result GetLegalInformation(nn::ncm::ContentId*, nn::ncm::ApplicationId, u32);
		Result GetPatchId(nn::ncm::PatchId*, nn::ncm::ContentMetaKey const&);
		Result GetProgram(nn::ncm::ContentId*, nn::ncm::ProgramId, u32);
		Result GetRequiredApplicationVersion(u32*, nn::ncm::ContentMetaKey const&);
		Result GetRequiredSystemVersion(u32*, nn::ncm::ContentMetaKey const&);
		Result GetSize(u64*, nn::ncm::ContentMetaKey const&);
		Result Has(bool*, nn::ncm::ContentMetaKey const&);
		Result HasAll(bool*, nn::ncm::ContentMetaKey const*, s32);
		Result HasContent(bool*, nn::ncm::ContentMetaKey const&, nn::ncm::ContentId const&);
		Result ListContentInfo(s32*, nn::ncm::ContentInfo*, s32, nn::ncm::ContentMetaKey const&, s32);
		Result ListContentMetaInfo(s32*, nn::ncm::ContentMetaInfo*, s32, nn::ncm::ContentMetaKey const&, s32);
		Result LookupOrphanContent(bool*, nn::ncm::ContentId const*, s32);
		Result Remove(nn::ncm::ApplicationId, u32);
		Result Remove(nn::ncm::ContentMetaKey);
		Result Remove(nn::ncm::SystemDataId, u32);
		Result Remove(nn::ncm::SystemProgramId, u32);
		Result Set(nn::ncm::ContentMetaKey const&, void const*, u64);
		Result operator=(nn::ncm::ContentMetaDatabase&&);
		Result swap(nn::ncm::ContentMetaDatabase&);
	};
}