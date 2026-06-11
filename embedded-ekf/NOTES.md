# Notes

- The user wants one lesson per math concept, with an immediate C function or module.
- The user wants to be involved in a fair amount of the building.
- Default pattern: lesson, reference, red test, narrow stub, user implementation, review.
- Keep examples rocket/OBC shaped without integrating into the OBC during course v1.
- Use C99, `eskf_real_t`, fixed-size arrays, static allocation, no heap, no VLAs.
- Make frame conventions and repeated-call contracts explicit, not implicit in tests only.
- Keep comments short and purpose-level. Do not turn stubs into walkthrough solutions.
- Future lesson pages may be created ahead of the active C tests, but active red tests should normally advance one lesson at a time.
