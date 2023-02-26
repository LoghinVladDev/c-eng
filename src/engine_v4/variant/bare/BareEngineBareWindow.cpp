/*
 * Created by loghin on 27/12/22.
 */

#include <base/Engine.hpp>
#include <base/storage/Storage.hpp>

#include <impl/glfw/Glfw.hpp>

#include <CDS/HashMap>
#include <CDS/filesystem/Path>
#include <CDS/util/JSON>
#include <CDS/threading/Thread>

#include <iostream>
#include <fstream>

#include <chrono>
#include <ctime>
#include <csignal>

using namespace cds;
using namespace cds::filesystem;
using namespace cds::json;
using namespace engine;
using namespace engine::storage;
using namespace engine::io;

class BareStorageNode : public Node {
private:
    JsonObject & _nodeImpl;

public:
    BareStorageNode (JsonObject & node) noexcept : _nodeImpl(node) {}

    ~BareStorageNode () noexcept override = default;
    __CDS_NoDiscard __CDS_cpplang_ConstexprOverride auto className () const noexcept -> cds::StringView override {
        return "BareStorageNode";
    }

    __CDS_NoDiscard auto get (StringView key) const noexcept -> AnyOrNone override {
        auto valueIt = this->_nodeImpl.find (key);
        if (valueIt == this->_nodeImpl.end()) { return nullptr; }
        if (valueIt->value().isInt()) { return valueIt->value().getInt(); }
        if (valueIt->value().isFloat()) { return valueIt->value().getFloat(); }
        if (valueIt->value().isString()) { return valueIt->value().getString(); }
        return nullptr;
    }

    auto set (StringView key, AnyOrNone data) noexcept -> void override {
        if (data.is <std::nullptr_t>()) { return; }
        data.ifIs <int> ([key, this](int value) { _nodeImpl.put (key, value); });
        data.ifIs <float> ([key, this](float value) { _nodeImpl.put (key, value); });
        data.ifIs <StringView> ([key, this](StringView value) { _nodeImpl.put (key, value); });
    }
};

class BareStorage : public Storage {
private:
    JsonObject _storageImpl;
    HashMap <String, BareStorageNode> _nodeMap;

    static inline JsonObject        _emptyNodeData {"{}"};
    static inline BareStorageNode   _emptyNode     {_emptyNodeData};

public:

    ~BareStorage () noexcept override = default;
    __CDS_NoDiscard __CDS_cpplang_ConstexprOverride auto className () const noexcept -> cds::StringView override {
        return "BareStorage";
    }

    explicit BareStorage (Path const & path) noexcept {
        this->_storageImpl = loadJson (path);
        for (auto & keyPair : this->_storageImpl) {
            try {
                this->_nodeMap.emplace( keyPair.key(), keyPair.value().getJson() );
            } catch (Exception const & exception) {
                std::cerr << "Failed to load Base Storage Node : " << exception.message() << '\n';
            }
        }
    }

    __CDS_NoDiscard auto getNode (StringView key) noexcept -> Node & override {
        auto nodeIt = this->_nodeMap.find(key);
        if (nodeIt == this->_nodeMap.end()) {
            return this->_nodeMap.emplace (key, this->_storageImpl.emplace(key, "{}").value().getJson()).value();
        }

        return nodeIt->value();
    }

    __CDS_NoDiscard auto getNode (StringView key) const noexcept -> Node const & override {
        auto nodeIt = this->_nodeMap.find(key);
        if (nodeIt == this->_nodeMap.end()) {
            return _emptyNode;
        }

        return nodeIt->value();
    }

    auto reset () noexcept -> void override {}
    auto save () noexcept -> void override {}
};

class BareLogger : public engine::io::Logger {
private:
    Array <std::ostream *> _outputs;
    String                 _name;

public:
    explicit BareLogger (String name) : _name (std::move(name)) {}
    auto addOutput (std::ostream & out) { this->_outputs.pushBack (& out); }

    auto log (Level level, cds::StringView message) const noexcept -> void override {

        char timeBuffer [512U];
        tm timeStruct;
        auto time = std::chrono::system_clock::to_time_t (std::chrono::system_clock::now());

#if defined(__CDS_Platform_Linux)
        localtime_r ( & time, & timeStruct );
#else
        localtime_s ( & timeStruct, & time );
#endif

        (void) std::strftime (
                timeBuffer, 512U,
                "%d-%m-%Y-%H:%M:%S",
                & timeStruct
        );

        auto msg = String::f (
                "[time = %s][logger = %s][level = %s][thread = 0x%llx] -> %s",
                timeBuffer,
                this->_name.cStr(),
                levelToString (level),
                cds::Thread::currentThreadID(),
                message.cStr()
        );

        for (auto * pOut : this->_outputs) {
            auto & out = * pOut;
            out << msg << '\n';
        }
    }

    auto log (Level level, StringView message, StringView fileName, StringView functionName, long long int lineNumber) const noexcept -> void override {

        char timeBuffer [512U];
        tm timeStruct;
        auto time = std::chrono::system_clock::to_time_t (std::chrono::system_clock::now());

#if defined(__CDS_Platform_Linux)
        localtime_r ( & time, & timeStruct );
#else
        localtime_s ( & timeStruct, & time );
#endif

        (void) std::strftime (
                timeBuffer, 512U,
                "%d-%m-%Y-%H:%M:%S",
                & timeStruct
        );

        auto msg = String::f (
                "[%s:%d -> %s][time = %s][logger = %s][level = %s][thread = 0x%llx] -> %s",
                fileName.cStr(),
                lineNumber,
                functionName.cStr(),
                timeBuffer,
                this->_name.cStr(),
                levelToString (level),
                cds::Thread::currentThreadID(),
                message.cStr()
        );

        for (auto * pOut : this->_outputs) {
            auto & out = * pOut;
            out << msg << '\n';
        }
    }

    auto log (Level level, StringView message, StringView fileName, StringView functionName, long long int lineNumber, engine::Object const * pObject) const noexcept -> void override {

        char timeBuffer [512U];
        tm timeStruct;
        auto time = std::chrono::system_clock::to_time_t (std::chrono::system_clock::now());

#if defined(__CDS_Platform_Linux)
        localtime_r ( & time, & timeStruct );
#else
        localtime_s ( & timeStruct, & time );
#endif

        (void) std::strftime (
                timeBuffer, 512U,
                "%d-%m-%Y-%H:%M:%S",
                & timeStruct
        );

        auto msg = String::f (
                "[%s:%d -> %s][time = %s][logger = %s][level = %s][type = %s, object = 0x%llx, thread = 0x%llx] -> %s",
                fileName.cStr(),
                lineNumber,
                functionName.cStr(),
                timeBuffer,
                this->_name.cStr(),
                levelToString (level),
                pObject->className().cStr(),
                reinterpret_cast <cds::uint64> (pObject),
                cds::Thread::currentThreadID(),
                message.cStr()
        );

        for (auto * pOut : this->_outputs) {
            auto & out = * pOut;
            out << msg << '\n';
        }
    }
};

static Engine * pEngine = nullptr;
auto sigcbk (int sigv) -> void {

    if (pEngine != nullptr) {
        pEngine->requestShutdown();
    }
}

auto main (
        int                  argumentCount,
        char const * const * ppArguments
) noexcept -> int {

    signal (SIGTERM, & sigcbk);

    BareLogger engineLogger ("Engine Logger");
    engineLogger.addOutput (std::cout);

    BareLogger glfwLogger ("GLFW Logger");
    glfwLogger.addOutput (std::cout);

    engine::Engine engine;
    engine.setLogger (& engineLogger);
    pEngine = & engine;

    struct EngineImplData {
        cds::UniquePointer <engine::Glfw> pGlfw;
    };

    return engine
            .setBaseStorage (new BareStorage("./settings.json"))
            .setPreInitHook ([&](auto * pEngine){

                auto * pImplData    = new EngineImplData;
                pImplData->pGlfw    = new Glfw();
                pImplData->pGlfw->setLogger (& glfwLogger);

                pEngine->setUserData(static_cast <void *> (pImplData));
            })
            .setPostShutdownHook ([&](auto * pEngine) {

                auto * pImplData = static_cast <EngineImplData *> (pEngine->userData());
                pImplData->pGlfw.reset();
                std :: cout << "shutdown\n";
            })
            .run (argumentCount, ppArguments);
}
