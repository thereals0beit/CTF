#pragma once

enum NPCStateTransitionType
{
	EndConversationTransition = 0x0,
	ContinueConversationTransition = 0x1,
	ShopTransition = 0x2,
};

struct NPCStateTransition
{
	std::basic_string<char, std::char_traits<char>, std::allocator<char> > text;
	NPCStateTransitionType type;
	std::basic_string<char, std::char_traits<char>, std::allocator<char> > nextState;
};

struct NPCState
{
	std::basic_string<char, std::char_traits<char>, std::allocator<char> > text;
	std::vector<NPCStateTransition, std::allocator<NPCStateTransition> > transitions;
};

struct NPC
{
	Actor baseclass_0;
	std::map<std::basic_string<char, std::char_traits<char>, std::allocator<char> >, NPCState, std::less<std::basic_string<char, std::char_traits<char>, std::allocator<char> > >, std::allocator<std::pair<std::basic_string<char, std::char_traits<char>, std::allocator<char> > const, NPCState> > > m_states;
};