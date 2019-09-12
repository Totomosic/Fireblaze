#pragma once
#include "clientpch.h"

namespace Fireblaze
{

	struct FBL_API ColoredWord
	{
	public:
		Bolt::Color Color;
		blt::string Word;
	};

	struct FBL_API ChatMessage
	{
	public:
		std::vector<ColoredWord> Words;
	};

	class FBL_API FireblazeChat
	{
	public:
		struct FBL_API ChatMessageInfo
		{
			ChatMessage Message;
			std::vector<UIText*> TextElements;
		};

	private:
		Layer* m_Layer;
		UIRectangle* m_ChatBackground;
		std::vector<ChatMessageInfo> m_Messages;
		ResourcePtr<Font> m_Font;

	public:
		FireblazeChat(Layer* layer);

		Layer& GetLayer() const;
		UIRectangle& GetChatBackground() const;

		void Show();
		void Hide();
		Vector2f GetSize();
		void SetSize(const Vector2f& size);
		void SetFont(const ResourcePtr<Font>& font);

		const std::vector<ChatMessageInfo>& GetMessageHistory() const;
		void Post(const ChatMessage& message);
		void Post(const blt::string& message);

		void Redraw();

	private:
		std::vector<UIText*> CreateChatTextElements(const ChatMessage& message);

	};

}