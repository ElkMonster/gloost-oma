
/*
                       ___                            __
                      /\_ \                          /\ \__
                   __ \//\ \     ___     ___     ____\ \  _\
                 /'_ `\ \ \ \   / __`\  / __`\  /  __\\ \ \/
                /\ \ \ \ \_\ \_/\ \ \ \/\ \ \ \/\__   \\ \ \_
                \ \____ \/\____\ \____/\ \____/\/\____/ \ \__\
                 \/___/\ \/____/\/___/  \/___/  \/___/   \/__/
                   /\____/
                   \_/__/

                   OpenGL framework for fast demo programming

                             http://www.gloost.org

    This file is part of the gloost framework. You can use it in parts or as
       whole under the terms of the GPL (http://www.gnu.org/licenses/#GPL).

            gloost is being created by Felix Weiﬂig and Stephan Beck

     Felix Weiﬂig (thesleeper@gmx.net), Stephan Beck (stephan@pixelstars.de)
*/



#ifndef GLOOST_SHADERCORE_H
#define GLOOST_SHADERCORE_H



/// gloost system includes
#include <graph/Core.h>
#include <Shader.h>



/// cpp includes
#include <GL/glew.h>
#include <stack>



namespace gloost
{

  class Action;
  class UniformSet;


 /// Core to set a shader for the following subgraph

class ShaderCore : public Core
{
	public:

		/// class constructor with a shader
		ShaderCore(Shader *shader);
		/// class constructor with a uniformSet
		ShaderCore(UniformSet* uSet);
		/// class constructor with a shader and a uniformSet
		ShaderCore(Shader *shader, UniformSet* uSet);


		/// class constructor
		ShaderCore(const std::string& vsFile, const std::string& fsFile);

		/// class destructor
		~ShaderCore();

		/* virtual */ void enterCore(const Action* action);
		/* virtual */ void exitCore (const Action* action);

    /// set the shader for this core
		void setShader(Shader* shader);
    /// get the shadeGLOOST_SHADERCORE_Hr for this core
		Shader* getShader() const;

		void  setUniformSet(UniformSet* uSet);
		UniformSet* getUniformSet() const;

  private:

    Shader*     _shader;
    UniformSet* _uniformSet;

    /// Needed to get the shader that was set befor if a action goes up in the graph
    /// to support multiple context each context gets its own stack
    static std::vector< std::stack<Shader*> > _shaderStackVector;

};


} // namespace gloost

#endif // GLOOST_SHADERCORE_H
