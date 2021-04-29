//
// Created by zephyrus on 23.04.21.
//

#ifndef PHYSICSSYSTEM_H
#define PHYSICSSYSTEM_H
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>


enum class CollisionType{
	IGNORE,
	OVERLAP,
	BLOCK
};

constexpr CollisionType operator&(CollisionType lsh, CollisionType rhs){ return CollisionType(std::min(int(lsh), int(rhs)));}

class Collider;
class PhysicsSystem;

class CollisionScheme{
public:
	class Builder{
		friend class CollisionScheme;
		std::string name_;
		std::unordered_map<std::string, CollisionType> collisions_;
	public:
		Builder(std::string name);
		Builder& addCollisionType(std::string name, CollisionType type);
		CollisionScheme build();
	};

	std::string getName() const;


	std::size_t hash() const{
		return std::hash<std::string>{}(name_);
	}

	friend bool operator==(const CollisionScheme &a, const CollisionScheme &b) {return a.name_ == b.name_;}
	friend bool operator!=(const CollisionScheme &a, const CollisionScheme &b) {return !(a == b);}

private:
	friend class PhysicsSystem;
	std::string name_;
	std::unordered_map<std::string, CollisionType> collisions_;
	CollisionScheme(Builder *builder);

};

namespace std{
	template<> struct hash<CollisionScheme>{
		using argument_type [[maybe_unused]] = CollisionScheme;
		using result_type [[maybe_unused]] = std::size_t;
		result_type operator()(const argument_type &f) const
		{
			return f.hash();
		}
	};
}

class PhysicsSystem{
	friend class CollisionScheme;
	friend class CollisionScheme::Builder;

	static std::vector<std::weak_ptr<Collider>> colliders;
	static std::unordered_set<std::string> colliderNames;
	static std::unordered_set<CollisionScheme> colliderSchemes;
public:

	static void init();
	static void update(double dt);
	static void addCollider(std::weak_ptr<Collider> collider);
	static void checkCollision(std::weak_ptr<Collider> collider);
	static void addColliderNames(std::initializer_list<std::string> names);
	static void addCollisionScheme(CollisionScheme scheme);

	static CollisionType getCollisionType(const std::string& lhs, const std::string& rhs);
};

#endif //PHYSICSSYSTEM_H
