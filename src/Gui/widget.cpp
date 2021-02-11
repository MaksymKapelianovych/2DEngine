#include "widget.h"

#include "shader.h"
#include "constants.h"
#include "scene.h"
#include "Components/component.h"
#include "utils.h"

glm::vec3 Widget::getPosition() const
{
    return m_position;
}

void Widget::setPosition(const glm::vec3 &value)
{
    m_position = value;
}

Scene *Widget::getScene() const
{
    return scene_;
}

void Widget::addComponent(Component *comp)
{
    for(Component *c: components){
        if(c->type() == comp->type()){
            delete c;
            return;
        }
    }

    components.push_back(comp);
    //comp->addObject(this);
}

Widget::Widget(Scene* parent, const glm::vec3 &pos): scene_(parent), m_position(pos), m_matrixPos(glm::vec4(1.f)), m_shader(nullptr)
{
    //add location component
}

Widget::~Widget(){
    for(Component *component: components){
        //component->removeObject(this);
    }
    delete m_shader;
}

bool Widget::mouse_callback(double xpos, double ypos)
{

}

void Widget::move(const glm::vec3 &offset)
{
    m_position += offset;
}

glm::vec2 Widget::getScreenPos()
{
    glm::mat4 model = glm::mat4(1.f);
    model = glm::translate(model, m_position);

    m_matrixPos = glm::vec4(scene_->getProjection() * scene_->getView() * model * glm::vec4(0.f, 0.f, 0.f, 1.0f));

    glm::vec2 pos = glm::vec2(scene_->getWidth()/2+scene_->getWidth()/2*m_matrixPos.x/m_matrixPos.w,
                              scene_->getHeight()/2-scene_->getHeight()/2*m_matrixPos.y/m_matrixPos.w);
    pos += scene_->getWindowPos();
    return pos;
}

glm::vec4 Widget::getMatrixPos()
{
    return m_matrixPos;
}

void Widget::setPos(const glm::vec3 &pos)
{
    m_position = pos;
}

Type Widget::getType()
{
    return Type::Drawable;
}

void Widget::draw()
{

}
