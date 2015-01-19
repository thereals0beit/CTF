#pragma once

struct Socket;

struct SocketVtbl
{
	void *(__thiscall *__vecDelDtor)(Socket *pthis, unsigned int);
	bool(__thiscall *Read)(Socket *pthis, void *, unsigned int);
	bool(__thiscall *Write)(Socket *pthis, const void *, unsigned int);
};

struct Socket
{
	SocketVtbl *vfptr;
	std::string m_lastErrorMessage;
};

struct WriteStream
{
	Socket *m_sock;
	std::vector<unsigned char, std::allocator<unsigned char> > m_buffer;
};

struct TCPSocket : public Socket
{
	unsigned int m_socket;
};

struct ThreadActionQueue
{
	std::mutex m_mutex;
	std::vector<std::function<void __cdecl(void)>, std::allocator<std::function<void __cdecl(void)> > > m_actions;
};

struct ServerThread
{
	std::string m_host;
	unsigned __int16 m_serverPort;
	std::thread m_thread;
};

struct ServerConnection;

struct ServerConnectionVtbl
{
	const char *(__thiscall *GetServerType)(ServerConnection *pthis);
	void *(__thiscall *__vecDelDtor)(ServerConnection *pthis, unsigned int);
};

struct ServerConnection
{
	ServerConnectionVtbl *vfptr;
	bool m_running;
	bool m_valid;
	bool m_readyToDisconnect;
	std::thread m_thread;
	std::mutex m_mutex;
	std::queue<std::function<void __cdecl(void)>, std::deque<std::function<void __cdecl(void)>, std::allocator<std::function<void __cdecl(void)> > > > m_serverQueue;
	std::condition_variable m_serverQueueEvent;
	ThreadActionQueue m_gameThreadActions;
};

struct GameServerConnection : public ServerConnection
{
	TCPSocket *m_sock;
	WriteStream m_writeStream;
	volatile bool m_tickInProgress;
};

struct SSLSocket : public Socket
{
	void *m_ssl;
};

struct MasterServerConnection : public ServerConnection
{
	void *m_context;
	SSLSocket *m_sock;
};