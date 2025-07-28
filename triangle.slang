static float2 positions[3] = float2[](
  float2(0.0, -0.5),
  float2(0.5, 0.5),
  float2(-0.5, 0.5)
);

static float3 colours[3] = float3[](
  float3(1.0, 0.0, 0.0),
  float3(0.0, 1.0, 0.0),
  float3(0.0, 0.0, 1.0)
);

struct VertexOutput {
  float4 svPositions : SV_Position;
  float3 colour;
};

[shader("vertex")] VertexOutput vertexShader(uint vertexId: SV_VertexID) {
  return VertexOutput(
    float4(positions[vertexId], 0.0, 1.0),
    colours[vertexId]
  );
}

[shader("fragment")] float4 fragmentShader(VertexOutput vertexOutput): SV_Target {
  return float4(vertexOutput.colour, 1.0);
}
