#include "HitBase.h"

C_HitBase::C_HitBase()
{
	m_pos = { 0.0f, 0.0f };
	m_radius = 0.0f;
}

C_HitBase::~C_HitBase()
{
}

void C_HitBase::Init()
{
}

void C_HitBase::Update()
{
}

bool C_HitBase::IsHit(const C_HitBase& other) const
{
	float dx = m_pos.x - other.m_pos.x;
	float dy = m_pos.y - other.m_pos.y;

	float distSq = dx * dx + dy * dy;
	float radiusSum = m_radius + other.m_radius;

	return distSq <= (radiusSum * radiusSum);
}