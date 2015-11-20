#include "SceneNode.hpp"
#include "Constants.h"
#include <iostream>
typedef std::shared_ptr<SceneNode> Ptr;

void SceneNode::attachChild(Ptr child) {
	child->mParent = this;
	mChildren.push_back(std::move(child));
}

Ptr SceneNode::detachChild(const SceneNode& node) {

	auto found = std::find_if(mChildren.begin(), mChildren.end(),
		[&] (Ptr& p) -> bool { return p.get() == &node; });

	assert(found != mChildren.end());

	Ptr result = std::move(*found);
	result->mParent = nullptr;
	mChildren.erase(found);
	return result;
}

void SceneNode::drawAll(sf::RenderTarget& target) {
	
	for(auto& child : mChildren) {
		if(child->isAlive()) {
			child->draw(target);
		}
	}
}

void SceneNode::updateAll(sf::Time deltaTime) {
	
	for(auto& child : mChildren) {
		child->update(deltaTime);
	}
	
}

std::vector<Ptr>& SceneNode::getChildren() {
	return mChildren;
}

SceneNode::~SceneNode(){}