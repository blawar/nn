#include "nn.h"

namespace nn::ncm
{
	Result ContentMetaDatabase::Set(const ContentMetaKey& contentMetaKey, const void* buffer, const u64 size)
	{
		return RequestV<0, Response, ContentMetaKey>(contentMetaKey).in(buffer, size).send(service()).result();
	}

	Result ContentMetaDatabase::Get(u64* size, void* buffer, const u64 maxSize, const ContentMetaKey& contentMetaKey)
	{
		return RequestV<1, ResponseV<u64>, ContentMetaKey>(contentMetaKey).out(buffer, maxSize).send(service()).result(size);
	}

	Result ContentMetaDatabase::Remove(const ContentMetaKey& contentMetaKey)
	{
		return RequestV<2, Response, ContentMetaKey>(contentMetaKey).send(service()).result();
	}

	Result ContentMetaDatabase::GetContentIdByType(ContentId* contentId, const ContentMetaKey& contentMetaKey, const ContentType& contentType)
	{
		return RequestVV<3, ResponseV<ContentId>, ContentType, ContentMetaKey>(contentType, contentMetaKey).send(service()).result(contentId);
	}

	Result ContentMetaDatabase::ListContentInfo(s32* size, ContentInfo* contentInfo, const s32 maxSize, const ContentMetaKey& contentMetaKey, s32 index)
	{
		return RequestVV<4, ResponseV<s32>, u32, ContentMetaKey>(index, contentMetaKey).in(contentInfo, maxSize).send(service()).result(size);
	}

	Result ContentMetaDatabase::GetLatest(ContentMetaKey* contentMetaKey, const u64 applicationId)
	{
		return RequestV<6, ResponseV<ContentMetaKey>, u64>(applicationId).send(service()).result(contentMetaKey);
	}

	Result ContentMetaDatabase::Has(bool* result, const ContentMetaKey& contentMetaKey)
	{
		return RequestV<8, ResponseV<bool>, ContentMetaKey>(contentMetaKey).send(service()).result(result);
	}

	Result ContentMetaDatabase::HasAll(bool* result, const ContentMetaKey* contentMetaKeys, const s32 size)
	{
		return Request<9, ResponseV<bool>>().in(contentMetaKeys, size).send(service()).result(result);
	}

	Result ContentMetaDatabase::GetSize(u64* size, const ContentMetaKey& contentMetaKey)
	{
		return RequestV<10, ResponseV<u64>, ContentMetaKey>(contentMetaKey).send(service()).result(size);
	}

	Result ContentMetaDatabase::GetRequiredSystemVersion(u32* version, const ContentMetaKey& contentMetaKey)
	{
		return RequestV<11, ResponseV<u32>, ContentMetaKey>(contentMetaKey).send(service()).result(version);
	}

	Result ContentMetaDatabase::GetPatchId(PatchId* patchId, const ContentMetaKey& contentMetaKey)
	{
		return RequestV<12, ResponseV<PatchId>, ContentMetaKey>(contentMetaKey).send(service()).result(patchId);
	}

	Result ContentMetaDatabase::DisableForcibly()
	{
		return Request<13, Response>().send(service()).result();
	}

	Result ContentMetaDatabase::LookupOrphanContent(bool* result, const ContentId* contentIds, s32 size)
	{
		return Request<14, ResponseV<bool>>().in(contentIds, size).send(service()).result(result);
	}

	Result ContentMetaDatabase::Commit()
	{
		return Request<15, Response>().send(service()).result();
	}

	Result ContentMetaDatabase::HasContent(bool* result, const ContentMetaKey& contentMetaKey, const ContentId& contentId)
	{
		return RequestVV<16, ResponseV<bool>, ContentMetaKey, ContentId>(contentMetaKey, contentId).send(service()).result(result);
	}

	Result ContentMetaDatabase::ListContentMetaInfo(s32* size, ContentMetaInfo* contentMetaInfos, const s32 maxSize, const ContentMetaKey& contentMetaKey, const s32 offset)
	{
		return RequestVV<17, ResponseV<s32>, ContentMetaKey, s32>(contentMetaKey, offset).in(contentMetaInfos, maxSize).send(service()).result(size);
	}

	Result ContentMetaDatabase::GetAttributes(u8* attributes, const ContentMetaKey& contentMetaKey)
	{
		return RequestV<18, ResponseV<u8>, ContentMetaKey>(contentMetaKey).send(service()).result(attributes);
	}

	Result ContentMetaDatabase::GetRequiredApplicationVersion(u32* version, const ContentMetaKey& contentMetaKey)
	{
		return RequestV<19, ResponseV<u32>, ContentMetaKey>(contentMetaKey).send(service()).result(version);
	}

	Result ContentMetaDatabase::GetContentIdByTypeAndIdOffset(ContentId* contentId, const ContentMetaKey& contentMetaKey, const ContentType contentType, const u8 offset)
	{
		return RequestVVV<20, ResponseV<ContentId>, ContentMetaKey, ContentType, u8>(contentMetaKey, contentType, offset).send(service()).result(contentId);
	}
}
