
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



/// gloost system includes
#include <graph/ShaderCore.h>
#include <graph/Action.h>
#include <UniformSet.h>
#include <gloostConfig.h>



namespace gloost
{



////////////////////////////////////////////////////////////////////////////////

 // Needed to get the shader that was set befor,
 // if a action goes up in the graph

/* static */
std::vector< std::stack<Shader*> > ShaderCore::_shaderStackVector = std::vector< std::stack<Shader*> >(GLOOST_SYSTEM_NUM_RENDER_CONTEXTS, std::stack<Shader*>());

////////////////////////////////////////////////////////////////////////////////


 /// class constructor

ShaderCore::ShaderCore(Shader *shader):
  Core(GLOOST_CORE_SHADER),
  _shader(shader),
  _uniformSet(0)
{
  _shader->takeReference();
}


////////////////////////////////////////////////////////////////////////////////


 /// class constructor

ShaderCore::ShaderCore(UniformSet* uSet):
  Core(GLOOST_CORE_SHADER),
  _shader(0),
  _uniformSet(uSet)
{
//  _uniformSet->takeReference();
}


////////////////////////////////////////////////////////////////////////////////


 /// class constructor

ShaderCore::ShaderCore(Shader *shader, UniformSet* uSet):
  Core(GLOOST_CORE_SHADER),
  _shader(shader),
  _uniformSet(uSet)
{
  _shader->takeReference();
}


////////////////////////////////////////////////////////////////////////////////


 // class constructor

ShaderCore::ShaderCore(const std::string& vsFile, const std::string& fsFile):
  Core(GLOOST_CORE_SHADER),
  _shader(0),
  _uniformSet(0)
{
  _shader = new Shader(vsFile, fsFile);
  _shader->takeReference();
}


////////////////////////////////////////////////////////////////////////////////


// class destructor
ShaderCore::~ShaderCore()
{
  if (_shader)
  {
    _shader->dropReference();
  }
}


////////////////////////////////////////////////////////////////////////////////


/* virtual */
void
ShaderCore::enterCore (const Action* action)
{
  if (_disabled)
  {
    return;

  }


  unsigned int currentContextId = action->getContextId();

  /// push this Shader to the stack and set it
  if (_shader)
  {
    _shaderStackVector[currentContextId].push(_shader);
    _shaderStackVector[currentContextId].top()->set(currentContextId);
  }

  /// configure the Shader with the UniformSet
  if (_uniformSet && _shaderStackVector[currentContextId].size())
  {
    _uniformSet->applyToShader(_shaderStackVector[currentContextId].top(),
                               currentContextId);
  }

}


////////////////////////////////////////////////////////////////////////////////


/* virtual */
void
ShaderCore::exitCore(const Action* action)
{
  if (_disabled)
  {
    return;
  }

  /// get context of the action
  unsigned int currentContextId = action->getContextId();

  if (_shader)
  {
    _shaderStackVector[currentContextId].top()->disable();
    _shaderStackVector[currentContextId].pop();
  }

  if (!_shaderStackVector[currentContextId].empty())
  {
    _shaderStackVector[currentContextId].top()->set(currentContextId);
  }
}


////////////////////////////////////////////////////////////////////////////////


void
ShaderCore::setShader (Shader *shader)
{
  _shader = shader;
}


////////////////////////////////////////////////////////////////////////////////


Shader*
ShaderCore::getShader () const
{
  return _shader;
}


////////////////////////////////////////////////////////////////////////////////


void
ShaderCore::setUniformSet(UniformSet* uSet)
{
  _uniformSet = uSet;
}


////////////////////////////////////////////////////////////////////////////////


UniformSet*
ShaderCore::getUniformSet() const
{
  return _uniformSet;
}


////////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////////

} // namespace gloost


