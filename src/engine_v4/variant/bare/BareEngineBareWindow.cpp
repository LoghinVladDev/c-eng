/*
 * Created by loghin on 27/12/22.
 */

#include "base/Engine.hpp"
#include "base/storage/Storage.hpp"

#include <CDS/HashMap>
#include <CDS/filesystem/Path>
#include <CDS/util/JSON>

using namespace cds;
using namespace cds::filesystem;
using namespace cds::json;
using namespace engine;
using namespace engine::storage;

class BareStorageNode : public Node {
private:
    JsonObject & _nodeImpl;

public:
    BareStorageNode (JsonObject & node) noexcept : _nodeImpl(node) {}

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

auto main (
        int                  argumentCount,
        char const * const * ppArguments
) noexcept -> int {

    engine :: Engine engine;

    return engine
            .setBaseStorage (new BareStorage("./settings.json"))
            .run (argumentCount, ppArguments);
}
