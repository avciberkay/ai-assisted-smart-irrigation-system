## Security Notes

Security is considered at both the device and backend levels.

Key measures:
- Backend services run inside Docker containers to reduce attack surface.
- Sensitive credentials and API keys are not stored in the public repository.
- MQTT communication can be secured using authentication and TLS.
- Reverse proxy handles HTTPS termination.
- Firewall rules restrict access to required ports only.

All configuration files shared in this repository are sanitized examples.
Production secrets and certificates are intentionally excluded.

