## Reverse Proxy (Nginx)

Nginx is used as a reverse proxy to expose backend services securely.

It routes external HTTP and HTTPS traffic to internal Docker services such as n8n.
TLS termination and domain-based routing are handled at this layer.

Nginx runs on the VPS and is configured to work alongside Dockerized services.
Only a sanitized reference configuration is documented in this repository.
