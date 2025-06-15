// pages/api/login.js
import { loginUsuario } from '@/lib/auth';
import { serialize } from 'cookie';

export default async function handler(req, res) {
  if (req.method !== 'POST') return res.status(405).end();

  const { username, password } = req.body;

  try {
    const token = await loginUsuario(username, password); // Chama a API REST externa

    res.setHeader('Set-Cookie', serialize('token', token, {
      httpOnly: true,
      secure: process.env.NODE_ENV === 'production',
      sameSite: 'lax',
      path: '/',
      maxAge: 60 * 60 * 24 // 1 dia
    }));

    res.status(200).json({ ok: true });
  } catch (err) {
    res.status(401).json({ error: 'Credenciais inválidas' });
  }
}

