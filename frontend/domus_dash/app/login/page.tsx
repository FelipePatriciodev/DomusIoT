"use client"; // se estiver usando app router (Next.js 13+)

import { useState } from "react";
import { useRouter } from "next/navigation"; // ou "next/router" se usar pages/required
import Link from 'next/link';

export default function Login() {
  const [username, setUsername] = useState('');
  const [password, setPassword] = useState('');
  const router = useRouter();

  const handleSubmit = async (e) => {
    e.preventDefault();

    const res = await fetch('/api/login', {
      method: 'POST',
      headers: { 'Content-Type': 'application/json' },
      body: JSON.stringify({ username, password }),
    });

    if (res.ok) {
      router.push('/dashboard');
    } else {
      alert('Usuário ou senha inválidos');
    }
  };
 
  return (
    <div className="bg-login flex justify-center items-center">
      <form className="bg-white w-[497px] h-[569px] rounded-lg flex flex-col items-center justify-center gap-6 p-6" onSubmit={handleSubmit}>
        <img src="/icon-DomusIoT.svg" alt="Logo" className="mb-4 w-24 h-24" />
        <input
          type="text"
          value={username}
          onChange={(e) => setUsername(e.target.value)}
          placeholder="Usuário"
          required
          className="w-[421px] h-[50px] rounded-xl border-2 border-gray-300 pl-3"
        />
        <input
          type="password"
          value={password}
          onChange={(e) => setPassword(e.target.value)}
          placeholder="Senha"
          required
          className="w-[421px] h-[50px] rounded-xl border-2 border-gray-300 pl-3"
        />
        <button
          type="submit"
          className="w-[421px] h-[50px] bg-[#004AAD] text-white rounded-xl"
        >Entrar</button>
        <p>
          Não possui uma conta? <Link href="\register">Cadastre-se</Link>
        </p>
      </form>
    </div>
  );
}

