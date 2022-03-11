#pragma once

namespace Framework
{
	class Core
	{
	public:
		// Initialize SDL and its components, returns false if failed
		bool initialize();

		void close();

	};
}


