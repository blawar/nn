#pragma once

#include "nn.h"

namespace nn::ncm
{
	class ContentId
	{
	public:
		u8 m_buffer[16];
	};

	class PlaceHolderId : public ContentId
	{
	};

	class ApplicationId
	{
	public:
		u64 m_id;
	};

	class RightsId
	{
	public:
		ApplicationId m_applicationId;
		u64 m_keyGen;
	};

	class PatchId : public ApplicationId
	{
	};

	class DataId : public ApplicationId
	{
	};

	class SystemId : public ApplicationId
	{
	};

	class SystemDataId : public ApplicationId
	{
	};

	class SystemProgramId : public ApplicationId
	{
	};

	class ProgramId : public ApplicationId
	{
	};

	class ContentInfo
	{
	};

	class ContentMetaInfo
	{
	};

	 enum class ContentType
	 {
		CNMT = 0,
		Program = 1,
		Data = 2,
		Icon = 3,
		Doc = 4,
		Info = 5
	};

	 enum class ContentMetaType
	 {
		 SystemProgram = 0x01,
		 SystemData = 0x02,
		 SystemUpdate = 0x03,
		 BootImagePackage = 0x04,
		 BootImagePackageSafe = 0x05,
		 Application = 0x80,
		 Patch = 0x81,
		 AddOnContent = 0x82,
		 Delta = 0x83,
	 };

	 enum class StorageId
	 {
		 None = 0,
		 Host = 1,
		 GameCard = 2,
		 NandSystem = 3,
		 NandUser = 4,
		 SdCard = 5
	 };
}

#include "IContentMetaDatabase.h"
#include "ContentMetaDatabase.h"

#include "IContentStorage.h"
#include "ContentStorage.h"

namespace nn::ncm
{
	static Result OpenContentMetaDatabase(ContentMetaDatabase*, const StorageId storageId);
	static Result OpenContentStorage(ContentStorage*, const StorageId storageId);

	static Service service();
}