/// OpenCL miner implementation.
///
/// @file
/// @copyright GNU General Public License

#pragma once

#include <fstream>

#include <libdevcore/Worker.h>
#include <libethcore/EthashAux.h>
#include <libethcore/Miner.h>

#include <boost/algorithm/string/predicate.hpp>
#include <boost/lexical_cast.hpp>

#pragma GCC diagnostic push
#if __GNUC__ >= 6
#pragma GCC diagnostic ignored "-Wignored-attributes"
#endif
#pragma GCC diagnostic ignored "-Wmissing-braces"

namespace dev
{
namespace eth
{
class VulkanMiner : public Miner
{
public:

    VulkanMiner(unsigned _index, VulkanSettings _settings, DeviceDescriptor& _device);
    ~VulkanMiner() override;

    static void enumDevices(std::map<string, DeviceDescriptor>& _DevicesCollection);

protected:
    bool initDevice() override;

    bool initEpoch_internal() override;

    void kick_miner() override;

private:
    
    void workLoop() override;

    void clear_buffer() {
        m_dag.clear();
        m_light.clear();
        m_header.clear();
        m_searchBuffer.clear();
        m_queue.clear();
        m_context.clear();
        m_abortqueue.clear();
    }

    unsigned m_dagItems = 0;
    uint64_t m_lastNonce = 0;

    VulkanSettings m_settings;

};

}  // namespace eth
}  // namespace dev
