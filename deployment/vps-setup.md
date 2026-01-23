## VPS Setup

The backend runs on a Linux-based Virtual Private Server.

The server is used to host all backend services required by the smart irrigation system.
Docker and Docker Compose are installed to ensure a reproducible and isolated environment.

High-level setup steps:
1. Provision a Linux VPS.
2. Install Docker and Docker Compose.
3. Configure firewall rules to allow only required ports.
4. Deploy backend services using Docker Compose.
5. Verify service health and connectivity.

This document intentionally omits provider-specific commands and credentials.
It describes the setup conceptually to allow replication on any VPS provider.

