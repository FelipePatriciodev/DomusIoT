"use client";

import { useState } from "react";
import { useRouter } from "next/navigation";

export default function Register() {
  const [username, setUsername] = useState('');
  const [email, setEmail] = useState('');
  const [password, setPassword] = useState('');
  const router = useRouter();

  const handleSubmit = async (e: React.FormEvent<HTMLFormElement>) => {
    e.preventDefault();

    const res = await fetch(`${process.env.NEXT_PUBLIC_API_URL}/api/auth/register`, {
      method: 'POST',
      headers: { 'Content-Type': 'application/json' },
      body: JSON.stringify({ username, email, password }),
    });

    if (res.ok) {
      router.push('/login');
    } else {
      const errorText = await res.text();
      alert('Registration failed: ' + errorText);
    }
  };

  return (
    <div className="bg-login flex justify-center items-center min-h-screen">
      <form
        className="bg-white w-[497px] h-[569px] rounded-lg flex flex-col items-center justify-center gap-6 p-6 shadow-md"
        onSubmit={handleSubmit}
      >
        <img src="/icon-DomusIoT.svg" alt="DomusIoT Logo" className="mb-4 w-24 h-24" />
        <input
          type="text"
          value={username}
          onChange={(e) => setUsername(e.target.value)}
          placeholder="Username"
          required
          className="w-[421px] h-[50px] rounded-xl border-2 border-gray-300 pl-3"
        />
        <input
          type="email"
          value={email}
          onChange={(e) => setEmail(e.target.value)}
          placeholder="Email"
          required
          className="w-[421px] h-[50px] rounded-xl border-2 border-gray-300 pl-3"
        />
        <input
          type="password"
          value={password}
          onChange={(e) => setPassword(e.target.value)}
          placeholder="Password"
          required
          className="w-[421px] h-[50px] rounded-xl border-2 border-gray-300 pl-3"
        />
        <button
          type="submit"
          className="w-[421px] h-[50px] bg-[#004AAD] text-white rounded-xl"
        >
          Register
        </button>
      </form>
    </div>
  );
}