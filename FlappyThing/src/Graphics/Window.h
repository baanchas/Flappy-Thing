#pragma once

namespace Engine {namespace Graphics {

	struct WindowProperties
	{
		std::string Title = "Flappy thing";

		uint32_t Width = 1280;
		uint32_t Height = 720;

		bool VSync = true;
	};

	class Window
	{
	public:
		Window();
		~Window();

		void Init(WindowProperties props);

		inline sf::RenderWindow* GetNativeWindow() { return m_NativeWindow; }

		void Clear();
		void Display();
		void Render(sf::Drawable& obj);

	private:
		uint32_t m_Width;
		uint32_t m_Height;
		uint32_t m_PositionX;
		uint32_t m_PositionY;

		bool m_VSync;

		std::string m_Title;
		
		sf::RenderWindow* m_NativeWindow;
	};

}}