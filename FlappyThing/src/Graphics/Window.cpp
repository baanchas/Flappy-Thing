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
	}

	void Window::Init(WindowProperties props)
	{
		m_NativeWindow = new sf::RenderWindow(sf::VideoMode(props.Width, props.Height), props.Title);

		m_Width = props.Width;
		m_Height = props.Height;
		m_Title = props.Title;
	}

	void Window::Clear()
	{
		m_NativeWindow->clear();
	}

	void Window::Display()
	{
		m_NativeWindow->display();
	}

}}