#pragma once
#include "Core.h"
#include "Shader.h"
#include "Framebuffer.h"

namespace Gel {

	class GEL_API PostProcessingEffect
	{
	public:
		PostProcessingEffect();
		~PostProcessingEffect();
		virtual void Use() = 0;
		void BeginCapture();
		void EndCapture();
		void PassScreenTexture(int index);
	protected:
		Shader* shader;
	private:
		Framebuffer framebuffer;
	};

}