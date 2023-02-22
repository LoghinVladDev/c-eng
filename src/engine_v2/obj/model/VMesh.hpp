//
// Created by vladl on 10/5/2020.
//

#ifndef ENG1_VMESH_H
#define ENG1_VMESH_H

#include <ecm/VComponent.hpp>

#include <VCommandPool.hpp>
#include <VVertexBuffer.hpp>
#include <VIndexBuffer.hpp>

namespace engine {

    class VMesh : public VComponent {
    private:
        //// private variables
        VCommandPool            const * _pCommandPool           {nullptr};
        VQueueFamilyCollection  const * _pQueueFamilyCollection {nullptr};
        VVertexBuffer                   _vertexBuffer;
        VIndexBuffer                    _indexBuffer;

        //// private functions

        explicit VMesh ( uint64 ignoredIDConstructor ) noexcept : VComponent( VComponent::DISTINCT | VComponent::HAS_DEPENDENCY, ignoredIDConstructor ) { }

#if __cpp_constexpr >= 201907
        [[nodiscard]] constexpr auto typeFlag () const noexcept -> TypeFlag override { return VComponent::TypeFlag::V_MESH; }
#else
        [[nodiscard]] inline auto typeFlag () const noexcept -> TypeFlag override { return VComponent::TypeFlag::V_MESH; }
#endif

        friend auto reconstructCacheBranch (VEntity *) noexcept -> void;

    public:
        //// public variables
        const static VMesh EMPTY;

        //// public functions
        [[nodiscard]] auto toString () const noexcept -> String override {
            return String().append("VMesh {\n")
                .append("\tcommandPool address = ").append(reinterpret_cast<uint64>(this->_pCommandPool)).append("\n")
                .append("\tqueueFamilyCollection address = ").append(reinterpret_cast<uint64>(this->_pQueueFamilyCollection)).append("\n")
                .append("\tvertexBuffer = ").append(this->_vertexBuffer.toString()).append("\n")
                .append("\tindexBuffer = ").append(this->_indexBuffer.toString()).append("\n")
                .append("}");
        }

        [[nodiscard]] auto className () const noexcept -> ClassName override {
            return "VMesh";
        }

        explicit VMesh(VEntity * pParent = nullptr) noexcept :
            VComponent(VComponent::Tag::DISTINCT | VComponent::Tag::HAS_DEPENDENCY, pParent) {

        }

        ~VMesh () noexcept override = default;

        [[nodiscard]] auto setup(
                VCommandPool                    const &,
                VQueueFamilyCollection          const &,
                std::vector < engine::VVertex > const &,
                std::vector < uint16 >          const &
        ) noexcept -> VulkanResult;

        auto free() noexcept -> void;
        auto clear() noexcept -> void;

        [[nodiscard]] constexpr auto getVertexBuffer () const noexcept -> VVertexBuffer const &  {
            return this->_vertexBuffer;
        }

        [[nodiscard]] constexpr auto getVertexBuffer () noexcept -> VVertexBuffer & {
            return this->_vertexBuffer;
        }

        [[nodiscard]] constexpr auto getIndexBuffer () const noexcept -> VIndexBuffer const & {
            return this->_indexBuffer;
        }

        [[nodiscard]] constexpr auto getIndexBuffer () noexcept -> VIndexBuffer & {
            return this->_indexBuffer;
        }

        [[nodiscard]] constexpr auto getLogicalDevicePtr () const noexcept -> VLogicalDevice const * {
            if ( this->_pCommandPool == nullptr )
                return nullptr;
            return this->_pCommandPool->getLogicalDevicePtr();
        }

        [[nodiscard]] auto copy () const noexcept -> VMesh * override {
            return new VMesh(*this);
        }

        [[nodiscard]] auto hash () const noexcept -> Index override {
            return this->_indexBuffer.hash() + this->_vertexBuffer.hash();
        }

        [[nodiscard]] inline auto operator == (VMesh const & o) const noexcept -> bool {
            if ( this == & o ) return true;
            return this->_vertexBuffer == o._vertexBuffer && this->_indexBuffer == o._indexBuffer;
        }

        [[nodiscard]] auto equals (Object const & o) const noexcept -> bool override {
            if ( this == & o ) return true;
            auto p = dynamic_cast < decltype ( this ) > ( & o );
            if ( p == nullptr ) return false;

            return this->operator== (*p);
        }
    };

}


#endif //ENG1_VMESH_H
