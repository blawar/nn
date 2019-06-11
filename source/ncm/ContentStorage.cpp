#include "nn.h"

namespace nn::ncm
{
	Result ContentStorage::CreatePlaceHolder(const PlaceHolderId& placeHolderId, const ContentId& contentId, const s64 size)
	{
		return RequestVV<1, Response, ContentId, PlaceHolderId>(contentId, placeHolderId).send(service()).result();
	}

	Result ContentStorage::Delete(ContentId contentId)
	{
		return RequestV<6, Response, ContentId>(contentId).send(service()).result();
	}

	Result ContentStorage::Has(bool* result, ContentId contentId)
	{
		return RequestV<7, ResponseV<bool>, ContentId>(contentId).send(service()).result(result);
	}

	Result ContentStorage::DeletePlaceHolder(const PlaceHolderId& placeHolderId)
	{
		return RequestV<2, Response, PlaceHolderId>(placeHolderId).send(service()).result();
	}
}