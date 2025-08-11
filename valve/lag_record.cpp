#include "lag_record.h"

#include "valve/client_state.h"
#include "valve/net_channel.h"
#include "valve/global_vars_base.h"

#include "client/client.h"

bool lag_record_t::valid() {
  auto channel = client::g_interfaces.client_state->net_channel;
  if (!channel)
    return false;

  auto correct = std::clamp<float>(channel->get_latency(FLOW_OUTGOING) +
                                       channel->get_latency(FLOW_INCOMING) +
                                       client::g_lag_compensation.get_lerp_time(),
                                   0.0f, 1.0f);

  return std::fabs(correct - (client::g_interfaces.global_vars->cur_time -
                              this->simulation_time)) <= 0.2f;
}