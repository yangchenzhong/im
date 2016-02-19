#include "socket.h"
#include "common.h"
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <fcntl.h>

/*将本机字节序转换为网络*/
uint32_t htonlv(uint32_t host)
{
	return htonl(host);
}

/*将网络转本机*/
uint32_t ntohlv(uint32_t net)
{
	return ntohl(net);
}

/*将本机字节序转换为网络*/
uint16_t htonsv(uint16_t host)
{
	return htons(host);
}

/*将网络转本机*/
uint16_t ntohsv(uint16_t net)
{
	return ntohs(net);
}

/*创建socket*/
int socket(int domain, int socktype, int protocol)
{
	return socket(domain, socktype, protocol);
}

/*将ip转换为网路字节序列*/
int iptonet(int domain, const char *ip, void *addr)
{
	return inet_pton(domain, ip, addr);
}

/*将网路序列转换为ip*/
const char *nettoip(int domain, const void *addr, char *desaddr, size_t len)
{
	return inet_ntop(domain, addr, desaddr, len);
}

int setsockaddrin(struct sockaddr_in *sockaddr, sa_family_t family, uint16_t port, char *ip)
{
	sockaddr->sin_family = family;
	sockaddr->sin_port = htons(port);
	if (iptonet(family, ip, &sockaddr->sin_addr) <= 0)
	{
		return FAILED;
	}

	return SUCCESS;
}

int getipaddrinfo(const char *host, const char *server,
				 	const struct addrinfo *hint, struct addrinfo **result)
{
	return getaddrinfo(host, server, hint, result);
}

void freeipaddrinfo(struct addrinfo *result)
{
	freeaddrinfo(result);
}

const char *gai_errorinfo(int errcode)
{
	return gai_strerror(errcode);
}

/*获取主机名和服务名*/
int gethostinfo(const struct sockaddr *addr, socklen_t socklen, char *host,
				 size_t hostlen, char *service, size_t serlen, int flag)
{
	return getnameinfo(addr, socklen, host, hostlen, service, serlen, flag);
}

/*绑定ip*/
int bindsock(int fd, const struct sockaddr *addr, socklen_t addrlen)
{
	return bind(fd, addr, addrlen);
}

/*监听链接*/
int listensock(int fd, int backlog)
{
	return listen(fd, backlog);
}

/*连接*/
int connectsock(int fd, struct sockaddr *addr, socklen_t addrlen)
{
	return connect(fd, addr, addrlen);
}

/*关闭*/
int closesock(int fd)
{
	return close(fd);
}

/*通过套接字获取IP和端口信息*/
int getsocketname(int fd, struct sockaddr *addr, socklen_t *addrlen)
{
	return getsockname(fd, addr, addrlen);
}

/*获取对端的套接字地址信息*/
int getpeersname(int peerfd, struct sockaddr *addr, socklen_t *addrlen)
{
	return getpeername(peerfd, addr, addrlen);
}

/*关闭一端通信*/
int shutdownsock(int fd, int how)
{
	return shutdown(fd, how);
}

/*设置tcp的选项*/
int setsocketopt(int fd, int level, int opt,
				 const void *optval, socklen_t optlen)
{
	return setsockopt(fd, level, opt, optval, optlen);
}

/*获取tcp的选项*/
int getsocketopt(int fd, int level, int opt,
				  void *optval, socklen_t *optlen)
{
	return getsockopt(fd, level, opt, optval, optlen);
}
/*创建tcp服务*/
int cretcpser(char *ip, int port)
{
	return SUCCESS;
}

/*创建udp服务*/
int creudpser(char *ip, int port)
{
	return SUCCESS;
}

/*创建unix服务*/
int creunixser(char *path)
{
	return SUCCESS;
}

/*设置非阻塞IO*/
int setnoblock(int fd)
{
	return fcntl(fd, F_SETFL, O_NONBLOCK);
}
