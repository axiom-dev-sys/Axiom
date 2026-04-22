#pragma once



namespace Axiom {
	
	class Component 
	{
	public:
		virtual ~Component() = default;

		virtual void onUpdate() {}
	};
}