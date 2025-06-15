"use client";

import { useState } from "react";
import { useRouter } from "next/navigation";
import Link from "next/link";
import Cookies from "js-cookie";

export default function Login() {
  const [username, setUsername] = useState("");
  const [password, setPassword] = useState("");
  const router = useRouter();

  const handleSubmit = async (e: React.FormEvent<HTMLFormElement>) => {
    e.preventDefault();

    try {
      const res = await fetch(`${process.env.NEXT_PUBLIC_API_URL}/api/auth/login`, {
        method: "POST",
        headers: { "Content-Type": "application/json" },
        body: JSON.stringify({ username, password }),
      });

      if (res.ok) {
        const data = await res.json();
        localStorage.setItem("token", data.token);

        Cookies.set("token", data.token, {
          expires: 1,
          sameSite: "strict",
          secure: process.env.NODE_ENV === "production",
        });

        router.push("/dashboard");
      } else {
        const error = await res.text();
        alert("Invalid username or password. " + error);
      }
    } catch {
      alert("Failed to connect to the server.");
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
          type="password"
          value={password}
          onChange={(e) => setPassword(e.target.value)}
          placeholder="Password"
          required
          className="w-[421px] h-[50px] rounded-xl border-2 border-gray-300 pl-3"
        />
        <button
          type="submit"
          className="w-[421px] h-[50px] bg-[#004AAD] text-white rounded-xl hover:bg-[#003a91]"
        >
          Sign In
        </button>
        <p>
          Don't have an account?{" "}
          <Link href="/register" className="text-blue-600 hover:underline">
            Register here
          </Link>
        </p>
      </form>
    </div>
  );
}