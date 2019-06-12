#pragma once

namespace nn::ncm
{
	class IContentMetaDatabase
	{
	public:
		const Service& service() { return m_service; }
	protected:
		Service m_service;
	};
}