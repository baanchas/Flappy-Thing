#include "ftpch.h"
#include "Window.h"


namespace Engine { namespace Graphics {

	Window::Window()
	{
		WindowProperties properties;

		Init(properties);

	}

	Window::~Window()
	{
		delete m_NativeWindow;
		delete m_Camera;
	}

	void Window::Init(WindowProperties props)
	{
		m_NativeWindow = new sf::RenderWindow(sf::VideoMode(props.Width, props.Height), props.Title);


		m_Width = props.Width;
		m_Height = props.Height;
		m_Title = props.Title;
		m_VSync = props.VSync;

		m_NativeWindow->setVerticalSyncEnabled(m_VSync);
		m_NativeWindow->setKeyRepeatEnabled(false);
	}

	void Window::Clear(sf::Color color)
	{
		m_NativeWindow->clear(color);
	}

	void Window::Display()
	{
		m_NativeWindow->display();
	}

	void Window::Render(sf::Drawable& obj)
	{
		m_NativeWindow->draw(obj);
	}

}}