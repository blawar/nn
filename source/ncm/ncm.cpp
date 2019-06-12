#include "nn.h"

namespace nn::ncm
{
	Service service()
	{
		Service s;
		return s;
	}

	Result OpenContentStorage(ContentStorage* contentStorage, const StorageId storageId)
	{
		return Request<4, ResponseS<ContentStorage>>().send(service()).result(contentStorage);
	}

	Result OpenContentMetaDatabase(ContentMetaDatabase* contentMetaDatabase, const StorageId storageId)
	{
		return Request<5, ResponseS<ContentMetaDatabase>>().send(service()).result(contentMetaDatabase);
	}
}
