//
// Created by Darwin Yuan on 2021/7/9.
//

#ifndef OBJECT_ARRAY_2_APPENDEXPORTER_06F980628AA149F1A6D9B9FD5687109A
#define OBJECT_ARRAY_2_APPENDEXPORTER_06F980628AA149F1A6D9B9FD5687109A

namespace mixin {
    template<typename T>
    struct AppendExporter : T {
        using T::Append;
        using T::Append_I;
    };
}

#endif //OBJECT_ARRAY_2_APPENDEXPORTER_06F980628AA149F1A6D9B9FD5687109A
