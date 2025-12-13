# Security Policy

## Supported Versions

| Version | Supported          |
| ------- | ------------------ |
| 0.1.x   | :white_check_mark: |

## Reporting a Vulnerability

If you discover a security vulnerability, please report it by:

1. **Do NOT** open a public issue
2. Email the maintainer directly or use GitHub's private vulnerability reporting
3. Include detailed steps to reproduce

We will respond within 48 hours and work with you to understand and address the issue.

## Security Considerations

LibOrganic intentionally corrupts memory as a feature. When using this library:

- Do not use `Organic<T>` for security-critical data that must remain intact
- The `NullifyStrategy` can be used for auto-expiring secrets
- Memory corruption is deterministic and logged — not suitable for cryptographic purposes
