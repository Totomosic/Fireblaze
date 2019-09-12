#include "clientpch.h"
#include "FireblazeChat.h"

namespace Fireblaze
{

	FireblazeChat::FireblazeChat(Layer* layer)
		: m_Layer(layer), m_ChatBackground(nullptr), m_Messages(), m_Font(ResourceManager::Get().Fonts().Default())
	{

	}

	Bolt::Layer& FireblazeChat::GetLayer() const
	{
		return *m_Layer;
	}

	Bolt::UIRectangle& FireblazeChat::GetChatBackground() const
	{
		return *m_ChatBackground;
	}

	void FireblazeChat::Show()
	{

	}

	void FireblazeChat::Hide()
	{

	}

	Bolt::Vector2f FireblazeChat::GetSize()
	{
		return {};
	}

	void FireblazeChat::SetSize(const Vector2f& size)
	{

	}

	void FireblazeChat::SetFont(const ResourcePtr<Font>& font)
	{

	}

	const std::vector<Fireblaze::FireblazeChat::ChatMessageInfo>& FireblazeChat::GetMessageHistory() const
	{
		return m_Messages;
	}

	void FireblazeChat::Post(const ChatMessage& message)
	{
		ChatMessageInfo info;
		info.Message = message;
		info.TextElements = CreateChatTextElements(message);
		m_Messages.push_back(info);
		Redraw();
	}

	void FireblazeChat::Post(const blt::string& message)
	{
		Post({ { { Color::Black, message } } });
	}

	void FireblazeChat::Redraw()
	{
		
	}

	std::vector<UIText*> FireblazeChat::CreateChatTextElements(const ChatMessage& message)
	{
		std::vector<UIText*> result;
		for (int i = 0; i < message.Words.size(); i++)
		{
			const ColoredWord& word = message.Words[i];
			
		}
		return result;
	}

}