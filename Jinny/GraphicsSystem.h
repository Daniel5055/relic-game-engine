#pragma once

#include <vector>

#include "GameSystem.h"

#include "MessageBoard.h"
#include "GraphicsMessage.h"

// Framework Dependencies
namespace Framework
{
	class Graphics;
	class Graphic;
	class Window;
}

namespace Jinny
{
	// Exclusively for GraphicSystem
	// GraphicSystem can store textures and fonts and assign texures
	class AssetManager;

	struct GraphicsMessage;

	/// <summary>
	/// Graphics System	
	/// 
	/// Dependencies
	/// - Asset Manager
	/// - Graphics Framework
	///
	/// Purpose
	/// - Load Textures and store to Asset Manager
	/// - Retrieve textures and assign to graphic
	/// - Render Graphic 
	///
	/// </summary>
	class GraphicsSystem : public GameSystem
	{
	public:
		// constructor
		GraphicsSystem();

		// ---  Main Functions ---
		// Initialization
		void initialize(Framework::Window* window, Framework::Graphics* graphics, MessageBoard<GraphicsMessage>* message_board);

		// Update
		void update();

		// Close
		void close();

		// destructor
		~GraphicsSystem();
	private:

		// --- Internal Functions ---
		// Message Handling
		void handleMessages();

		// --- Framework ---
		Framework::Graphics* f_graphics;
		Framework::Window* f_window;

		// --- Data ---

		// Jinny Dependencies
		AssetManager* m_asset_manager;
		MessageBoard<GraphicsMessage>* m_message_board;

		// Render list
		std::vector<Framework::Graphic*> m_graphic_ptrs;
		std::vector<Framework::Graphic*> m_gui_graphic_ptrs;

	};
}
