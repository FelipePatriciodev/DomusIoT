// pages/api/login.js
import { loginUsuario } from '@/lib/auth';
import { createUsuario } from '@/lib/auth';
import { serialize } from 'cookie';

export default async function handler(req, res) {
  if (req.method !== 'POST') return res.status(405).end();

  const { username, password } = req.body;

  try {
    const id = await createUsuario(username, password); // Chama a API REST externa

    res.status(200).json({ ok: true });
  } catch (err) {
    res.status(401).json({ error: 'Credenciais inválidas' });
  }
}

