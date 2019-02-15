
GLPROXY_NOINLINE static void* current_resolve(khronos_uint16_t offset) {
    tls_ptr tls = get_tls_by_index(glproxy_dispatch_common_tls_index);
    void** ptr = ((void**)&tls->current_dispatch_table) + offset;
    if (!*ptr) {
        struct dispatch_metadata *metadata = &tls->current_metadata;
        const khronos_uint16_t resolve_info_offset = metadata->resolve_offsets[offset];
        const struct dispatch_resolve_info *resolve_info = metadata->resolve_info_table + resolve_info_offset;
        const khronos_uint16_t target_identity = resolve_info->identity;
        const char* basic_name = metadata->entrypoint_strings + resolve_info->name_offset;
        if (tls->handles_opened == false) {
            glproxy_context_handles_open(tls);
            tls->handles_opened = true;
        }

        if (!metadata->inited) {
            current_glproxy_resolve_init(tls);
        }
        for (; target_identity == resolve_info->identity && *ptr == NULL; ++resolve_info) {
            const char* name = metadata->entrypoint_strings + resolve_info->name_offset;
            switch (resolve_info->resolve_type) {
#if HAS_DISPATCH_RESOLVE_DIRECT
            case DISPATCH_RESOLVE_DIRECT:
                current_glproxy_resolve_direct(tls, name, ptr);
                break;
#endif
#if HAS_DISPATCH_RESOLVE_VERSION
            case DISPATCH_RESOLVE_VERSION:
                current_glproxy_resolve_version(tls, name, ptr, resolve_info->condition);
                break;
#endif
            case DISPATCH_RESOLVE_EXTENSION: {
                current_glproxy_resolve_extension(tls, name, ptr, resolve_info->condition);
                break;
            }
            default:
                break;
            }
        }
        if (*ptr == NULL) {
          fprintf(stderr, "[glproxy] Resolve failed for function:%s\n", basic_name);
        }
    }

    return *ptr;
}

static void current_glproxy_dispatch_metadata_init(struct dispatch_metadata *data, bool glproxy_inited) {
    data->extensions_count = current_extensions_count;
    data->extension_offsets = current_extension_offsets;
    data->extension_enum_strings = current_extension_enum_strings;
    data->entrypoint_strings = (const char*)current_entrypoint_strings;
    data->resolve_info_table = current_resolve_info_table;
    data->resolve_offsets = current_resolve_offsets;
    data->method_name_offsets = current_method_name_offsets;
    data->method_count = sizeof(current_resolve_offsets) / sizeof(current_resolve_offsets[0]);
    if (!glproxy_inited) {
        init_dispatch_metadata_metadata(data);
    }
}
